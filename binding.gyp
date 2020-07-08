{
    "targets": [{
        "target_name": "advapi32js",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "msvs_settings": {
                "VCCLCompilerTool": {
                  "ExceptionHandling": 1,
                  "AdditionalOptions": [ "/std:c++17" ]
                }
              },
        "sources": [
            "src/cpp/impersonator.cpp",
            "src/cpp/helper.cpp",
            "src/cpp/addon.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ]
    }]
}