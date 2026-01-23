#!/bin/sh
set -e

VENDOR="MARS-Engineers"
ARCH="robotrix"
VERSION="1.0.2"
REPO_URL="https://github.com/MARS-Engineers/arduino-boards"
JSON_OUT="package_MARS-engineers_boards_index.json"
ZIP_NAME="${VENDOR}-boards-${VERSION}.zip"
#RELEASE_URL="${REPO_URL}/releases/download/${VERSION}/${ZIP_NAME}"
RELEASE_URL="${REPO_URL}/releases/download/test/${ZIP_NAME}"
ZIP_PATH="build/${ZIP_NAME}"
rm -f "$ZIP_PATH"

cd hardware
zip -rq ../"$ZIP_PATH" robotrix
cd ..

SIZE=$(stat -c %s "$ZIP_PATH")
SHA256=$(sha256sum "$ZIP_PATH" | awk '{print $1}')

echo "Size: " $SIZE "Sum: " $SHA256

sed \
  -e "s/__VERSION__/$VERSION/g" \
  -e "s#__URL__#$RELEASE_URL#g" \
  -e "s/__ZIP__/$ZIP_NAME/g" \
  -e "s/__SHA256__/$SHA256/g" \
  -e "s/__SIZE__/$SIZE/g" \
  package_index.template.json > "$JSON_OUT"
