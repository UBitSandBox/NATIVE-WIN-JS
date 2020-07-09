# WIN-IMPERSONATOR-JS

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e14ad54a68b14e958d6f42e32fcad19b)](https://app.codacy.com/gh/UBitSandBox/WIN-IMPERSONATOR-JS?utm_source=github.com&utm_medium=referral&utm_content=UBitSandBox/WIN-IMPERSONATOR-JS&utm_campaign=Badge_Grade_Dashboard)

## Impersonator for Windows 

Impersonator Object Factory with 2 public functions, "impersonateUser" and "stopImpersonation"

Calling COM Functions 

- LogonUserW (https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-logonuserw)

- ImpersonateLoggedOnUser (https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-impersonateloggedonuser)

- RevertToSelf (https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-reverttoself)


Reimplementing Code originally written by Simon Buchan https://github.com/simonbuchan/native-users-node (Thanks a lot!)

### Usage

```javascript
import {createObject, LogonProvider, LogonType} from "native-win-js-for-fun";

...
let impersonator = createObject(userName, password, domain);

//impersonating Windows Account, calling functions LogonUserW and also ImpersonateLoggedOnUser
impersonator.impersonateUser(LogonType.NETWORK, LogonProvider.WINNT50);

//stop Impersonation, calling functions RevertToSelf and then closing handle
//This function must be called, otherwise handle will not be closed!!!
impersonator.stopImpersonation();

```

