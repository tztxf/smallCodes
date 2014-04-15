/*
author  : tanxianfeng@baidu.com
date    : 2014.4.10
desc    : nshead pack
*/

module.exports = nshead;

function nshead(o){
    if(o!=null){
        this.id = o.id;
        this.version = o.version;
        this.log_id = o.log_id;
        this.provider = o.provider;
        this.magic_num = o.magic_num;
        this.reserved = o.reserved;
        this.body_len = o.body_len;
    }else{
        this.id = 0;
        this.version = 0;
        this.log_id = 0;
        this.provider = "";
        this.magic_num = -76508268;//0xfb709394;
        this.reserved = 0;
        this.body_len = 0;
    }
}

nshead.headlen = 36;

//Big-Endian
nshead.prototype.pack = function(){
    var buf = new Buffer(nshead.headlen);
    buf.writeInt16LE(this.id, 0);
    buf.writeInt16LE(this.version, 2);
    buf.writeInt32LE(this.log_id, 4);
    buf.write(this.provider, 8);
    buf.fill(0, 8+this.provider.length, 24);
    buf.writeInt32LE(this.magic_num, 24);
    buf.writeInt32LE(this.reserved, 28);
    buf.writeInt32LE(this.body_len, 32);
    return buf;
}

nshead.prototype.unpack = function(buf){
    var head = this;
    head.id = buf.readInt16LE(0);
    head.version = buf.readInt16LE(2);
    head.log_id = buf.readInt32LE(4);
    for(var i=8; i<24; i++){
        if(buf[i]==0){
            break;
        }
    }
    head.provider = buf.toString('utf-8', 8, i);
    head.magic_num = buf.readInt32LE(24);
    head.reserved = buf.readInt32LE(28);
    head.body_len = buf.readInt32LE(32);
    return head;
}
