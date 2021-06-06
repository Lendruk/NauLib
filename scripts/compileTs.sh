#!/bin/sh
if [ -d "./typescript/node_modules/"]
then
    sh ./typescript/node_modules/.bin/tsc --build tsconfig.json
    echo "Compiled typescript code"
else
    echo "Error node_modules does not exist please run npm install"
fi