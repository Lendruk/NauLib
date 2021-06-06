#!/usr/bin/env pwsh
if(Test-Path -Path "../typescript/node_modules") {
    & "../typescript/node_modules/.bin/tsc" "--build" "../typescript/tsconfig.json"
    "Compiling typescript"
} else {
    "node_modules not found"
}