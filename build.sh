BUILD_FILE="./build/MARS-engineers-boards-test.zip"
rm -f $BUILD_FILE

zip -rq $BUILD_FILE hardware/robotrix

SIZE=$(stat -c %s $BUILD_FILE)

echo "Size: " $SIZE