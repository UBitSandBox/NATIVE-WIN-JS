const native = require("bindings")("users.node");

export const LogonType = {
    INTERACTIVE: 2,
    NETWORK: 3,
    BATCH: 4,
    SERVICE: 5,
    UNLOCK: 7,
    NETWORK_CLEARTEXT: 8,
    NEW_CREDENTIALS: 9
};

export const LogonProvider = {
    DEFAULT:0,
    WINNT35:1,
    WINNT40:2,
    WINNT50:3,
    VIRTUAL:4
};

export function logonUser({name, password, domain, type, provider}){
    return native.logonUser(name, domain, password, type, provider);
}

export function impersonateLoggedOnUser({handle}){
    return native.impersonateLoggedOnUser(handle);
}

export function revertToSelf(){
    return native.revertToSelf();
}
