#!/bin/sh
set -e

VENDOR="MARS-Engineers"
VERSION=$(cat ./tools/version)
REPO_URL="https://github.com/MARS-Engineers/arduino-robotrix"

JSON_OUT="build/ package_MARS-engineers_boards_index.json "
old_json="build/temp/package_MARS-engineers_index_stable.json"
new_json="build/package_MARS-engineers_index-${VERSION}.json"

ZIP_NAME="${VENDOR}-boards-${VERSION}.zip"
RELEASE_URL="${REPO_URL}/releases/download/${VERSION}/${ZIP_NAME}"
ZIP_PATH="build/${ZIP_NAME}"

TEMP_PATH="build/temp"

mkdir -p $TEMP_PATH
rm -f "$ZIP_PATH"

cd hardware
zip -rq ../"$ZIP_PATH" rp2040
cd ..

SIZE=$(stat -c %s "$ZIP_PATH")
SHA256=$(sha256sum "$ZIP_PATH" | awk '{print $1}')

echo "Size: " $SIZE "Sum: " $SHA256


#create new package index
sed \
  -e "s/__VERSION__/$VERSION/g" \
  -e "s#__URL__#$RELEASE_URL#g" \
  -e "s/__ZIP__/$ZIP_NAME/g" \
  -e "s/__SHA256__/$SHA256/g" \
  -e "s/__SIZE__/$SIZE/g" \
  package_index.template.json > $new_json



# Get previous release name
#curl --silent https://api.github.com/repos/MARS-engineers/arduino-robotrix/releases > build/temp/releases.json
# Previous final release (prerelease == false)
#prev_release=$(jq -r '. | map(select(.draft == false and .prerelease == false)) | sort_by(.created_at | - fromdateiso8601) | .[0].tag_name' build/temp/releases.json)
# Previous release (possibly a pre-release)
#prev_any_release=$(jq -r '. | map(select(.draft == false)) | sort_by(.created_at | - fromdateiso8601)  | .[0].tag_name' build/temp/releases.json)
# Previous pre-release
#prev_pre_release=$(jq -r '. | map(select(.draft == false and .prerelease == true)) | sort_by(.created_at | - fromdateiso8601)  | .[0].tag_name' build/temp/releases.json)

#echo "Previous release: $prev_release"
#echo "Previous (pre-?)release: $prev_any_release"
#echo "Previous pre-release: $prev_pre_release"

#base_ver=$prev_pre_release


# Download previous release
#echo "Downloading base package: $base_ver"
#curl -L -o $old_json "https://github.com/MARS-engineers/arduino-robotrix/releases/download/${base_ver}/package_MARS-engineers_index-${base_ver}.json"
curl -L -o $old_json "https://github.com/MARS-engineers/arduino-robotrix/releases/download/global/package_MARS-engineers_boards_index.json"


python3 tools/merge_packages.py $new_json $old_json > $JSON_OUT

rm -rf $TEMP_PATH