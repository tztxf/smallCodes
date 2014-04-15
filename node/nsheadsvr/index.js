/*
author  : tanxianfeng@baidu.com
date    : 2014.4.10
desc    : nshead+mcpack server
*/
var net = require('net');
var events = require("events");
var util = require('util');
var nshead = require('./nshead.js');
var mcpack = require('./node_addons/mcpack');

function nsheadsvr(option){
    events.EventEmitter.call(this);
    this.name = option.name;
    this.port = option.port;
    this.type = option.type;
    this.server = null;
}
util.inherits(nsheadsvr, events.EventEmitter);

nsheadsvr.prototype.close = function(){
    this.server.close();
}

exports.createServer = createServer;

function createServer(option){
    var svr = new nsheadsvr(option);
    svr.server = net.createServer();
    svr.server.listen(svr.port);

    svr.server.on('listening', function(){
        svr.emit('listening');
        console.log(svr.name + ' begin listening');
    });

    svr.server.on('error', function(err){
        svr.emit('error');
        console.log(svr.name + 'error: ' + err);
    });

    svr.server.on('close', function(){
        svr.emit('close');
        console.log(svr.name + 'close');
    });

    svr.server.on('connection', function(c){
        console.log('server connected');
        var netdata;
        var d = [];
        var totalLength = 0;
        var state = 0;
        var head = new nshead();
        c.on('data', function(data){
            d.push(data);
            totalLength += data.length;
            if(state==0 && totalLength>=nshead.headlen){ // parse header
                var netdata = Buffer.concat(d, totalLength);
                var headbuf = netdata.slice(0, nshead.headlen);
                console.log(headbuf);
                head.unpack(headbuf);
                console.log(head);
                state = 1;
            }else if(state==1 && totalLength>=nshead.headlen+head.body_len){ // parse body
                var netdata = Buffer.concat(d, totalLength);
                var mcpackbuf = netdata.slice(nshead.headlen, nshead.headlen+head.body_len);
                var mcpackobj = mcpack.mcpackbuf_2_object(mcpackbuf);
                // build req & res
                var req = new request(c, svr.type, head, mcpackobj);
                var reshead = new nshead(head);
                reshead.provider = svr.name; // set provider
                console.log(reshead);
                var res = new response(request, reshead);
                res.connection_type = svr.type;
                svr.emit('request', req, res);
            }
        });
        c.on('end', function(){
            console.log('disconnected');
        });
    });

    return svr;
};

function request(c, type, header, mcpackobj){
    this.connection = c;
    this.connection_type = type;
    this.header = header;
    this.mcpack = mcpackobj;
}

request.prototype.abort = function(obj){
    if(this.connection_type==0){ //short connection
        this.connection.end();
    }
}

function response(req, header){
    this.request = req;
    this.connection_type = 0;
    this.head = header;
}

response.prototype.send = function(obj){
    var mcpackbuf = mcpack.object_2_mcpackbuf(obj);
    this.head.body_len = mcpackbuf.length;
    var headbuf = this.head.pack();
    this.connection.write(headbuf);
    this.connection.write(mcpackbuf);
    if(this.connection_type==0){ //short connection
        this.connection.end();
    }
}


