if(req.headers.origin) {
    res.header('Access-Control-Allow-Origin', req.headers.origin);
}
if(req.headers['access-control-request-method']) {
    res.header('Access-Control-Allow-Methods', req.headers['access-control-request-method']);
}
if(req.headers['access-control-request-headers']) {
    res.header('Access-Control-Allow-Headers', req.headers['access-control-request-headers']);
}
if(req.headers.origin){
    res.header('Access-Control-Allow-Origin', req.headers.origin);
}
res.header('Access-Control-Allow-Credentials', 'true');
