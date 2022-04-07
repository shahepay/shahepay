 #!/usr/bin/env bash

 # Execute this file to install the shahepay cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%shahepay-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/shahepay-Qt.app/Contents/MacOS/shahepayd /usr/local/bin/shahepayd
 sudo ln -s ${LOCATION}/shahepay-Qt.app/Contents/MacOS/shahepay-cli /usr/local/bin/shahepay-cli
