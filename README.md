# WIN-IMPERSONATOR-JS

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e14ad54a68b14e958d6f42e32fcad19b)](https://app.codacy.com/gh/UBitSandBox/WIN-IMPERSONATOR-JS?utm_source=github.com&utm_medium=referral&utm_content=UBitSandBox/WIN-IMPERSONATOR-JS&utm_campaign=Badge_Grade_Dashboard)

## Impersonator for Windows 

Impersonator Object Factory with 2 public functions, "impersonateUser" and "stopImpersonation"

Calling COM Functions 

- LogonUserW (https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-logonuserw)

- ImpersonateLoggedOnUser (https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-impersonateloggedonuser)

- RevertToSelf (https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-reverttoself)


Reimplementing Code originally written by Simon Buchan https://github.com/simonbuchan/native-users-node (Thanks a lot!)

###### Visual Studio Build Tools 2019

Manually: https://visualstudio.microsoft.com/fr/visual-cpp-build-tools/

Visual Studio Build Tools > 2017 are needed for win-permissions-js (C++ 17)!!!

```powershell
$buildToolsUrl="https://aka.ms/vs/16/release/vs_buildtools.exe"
$buildToolsPath=Join-Path $base_install_path 'BuildTools'

# Big mistake here, we should use Microsoft.VisualStudio.Component.VC.Tools.x86.x64 and Microsoft.VisualStudio.Component.VC.v141.x86.x64
# instead of Microsoft.VisualStudio.Workload.AzureBuildTools

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
Invoke-WebRequest -Uri $buildToolsUrl -OutFile "vs_buildtools.exe"
Start-Process -Wait -NoNewWindow -FilePath .\vs_buildtools.exe -ArgumentList '--quiet', '--wait', '--norestart', '--nocache', $('--installPath {0}' -f $buildToolsPath),
    '--add Microsoft.VisualStudio.Component.VC.CoreBuildTools',
    '--add Microsoft.VisualStudio.Component.VC.Redist.14.Latest',
    '--add Microsoft.VisualStudio.Component.Windows10SDK',
    '--add Microsoft.VisualStudio.Component.TestTools.BuildTools',
    '--add Microsoft.VisualStudio.Component.VC.ASAN',
    '--add Microsoft.VisualStudio.Component.VC.CMake.Project',
    '--add Microsoft.VisualStudio.Component.VC.Tools.x86.x64',
    '--add Microsoft.VisualStudio.Component.Windows10SDK.18362'

$env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")

```
###### Build Tools (Visual Studio Build Tools 2017 + Python 2.7) for gyp

https://www.npmjs.com/package/windows-build-tools

```powershell

npm config set proxy http://proxy.test.org:8080
npm config set https-proxy http://proxy.test.org:8080

npm install --global --production --add-python-to-path windows-build-tools

#Refreshing PATH Variable after build tools installation
$env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
```

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

