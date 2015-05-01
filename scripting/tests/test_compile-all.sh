#!/bin/bash

# Bash immediate exit and verbosity
set -ev

SMPATTERN="http:.*sourcemod-.*-linux.*"
SMURL="http://www.sourcemod.net/smdrop/$SMVERSION/"
SMPACKAGE=`lynx -dump "$SMURL" | egrep -o "$SMPATTERN" | tail -1`
TEST_SCRIPT="tests/test_compile-all.sp"

wget $SMPACKAGE
tar -xzf $(basename "$SMPACKAGE")
cp -R scripting/ addons/sourcemod/
cd addons/sourcemod/scripting/
chmod +x spcomp

# Semicolon fix for Sourcemod include file (hack)
sed -i 's/^\tnew i, len/\tnew i, len;/' ./include/string.inc

# Verify all functions stocks have been added to the test file
functions=$(grep -oP --color=never --no-filename '^(?!static\s+)stock\s*(\w+:)?\K\w+(?=\()' include/smlib/*.inc)

# Temporarily disable bash immediate exit
set +e
while read -r function; do
	grep -Fq "$function" "$TEST_SCRIPT"
    exit_code=$?

    if [[ $exit_code != 0 ]]; then
    	echo "[ERROR] Stock function \"$function\" not found in \"$TEST_SCRIPT\". Please add it."
    	exit 1
    fi
done <<< "$functions"
set -e


./spcomp -\; "$TEST_SCRIPT"

ls *.smx
