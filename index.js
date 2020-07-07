var native = require("bindings")("advapi32js.node");

var LogonType = {
    INTERACTIVE: 2,
    NETWORK: 3,
    BATCH: 4,
    SERVICE: 5,
    UNLOCK: 7,
    NETWORK_CLEARTEXT: 8,
    NEW_CREDENTIALS: 9
};

module.exports.LogonType = LogonType;

var LogonProvider = {
    DEFAULT:0,
    WINNT35:1,
    WINNT40:2,
    WINNT50:3,
    VIRTUAL:4
};

module.exports.LogonProvider = LogonProvider;

function logonUser({name, password, domain, type, provider}){
    return native.logonUser(name, domain, password, type, provider);
}

module.exports.logonUser = logonUser;

function impersonateLoggedOnUser({handle}){
    return native.impersonateLoggedOnUser(handle);
}

module.exports.impersonateLoggedOnUser = impersonateLoggedOnUser;

function revertToSelf(){
    return native.revertToSelf();
}

module.exports.revertToSelf = revertToSelf;
