#!/bin/bash
set -e

# ============================
# Ayarlar
# ============================
APP_NAME="C64KERNALGenesis"
BUILD_DIR="$PWD/build"
APPDIR="$PWD/AppDir"
QT_DIR="$HOME/Qt/6.11.0/gcc_64"
CMAKE_DIR="$HOME/Qt/Tools/CMake/bin"   # CMake yolu
ICON_PATH="$PWD/C64KERNALGenesis.png"  # 256x256 PNG simge yolu

# ============================
# PATH güncellemesi
# ============================
export PATH="$QT_DIR/bin:$CMAKE_DIR:$PATH"
echo "✅ PATH güncellendi: $QT_DIR/bin ve $CMAKE_DIR eklendi"

# qmake var mı kontrol et
if ! command -v qmake &> /dev/null
then
    echo "❌ qmake bulunamadı, PATH doğru mu?"
    exit 1
fi

# cmake var mı kontrol et
if ! command -v cmake &> /dev/null
then
    echo "❌ cmake bulunamadı, PATH doğru mu?"
    exit 1
fi

qmake --version
cmake --version

# ============================
# Temiz build
# ============================
rm -rf "$BUILD_DIR" "$APPDIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# ============================
# CMake ile derleme
# ============================
cmake .. -DCMAKE_PREFIX_PATH="$QT_DIR"
make -j$(nproc)

# ============================
# AppDir hazırlama
# ============================
cd "$PWD/.."
mkdir -p "$APPDIR/usr/bin"
mkdir -p "$APPDIR/usr/share/applications"
mkdir -p "$APPDIR/usr/share/icons/hicolor/256x256/apps"
mkdir -p "$APPDIR/usr/plugins/platforms"

# Binary kopyala
cp "$BUILD_DIR/$APP_NAME" "$APPDIR/usr/bin/"

# Qt’nin plugins/platforms içeriğini kopyala
cp $QT_DIR/plugins/platforms/* "$APPDIR/usr/plugins/platforms/"

# qt.conf oluştur
cat > "$APPDIR/usr/bin/qt.conf" <<EOL
[Paths]
Prefix=.
Plugins=../plugins
EOL

# .desktop dosyası oluştur
cat > "$APPDIR/usr/share/applications/$APP_NAME.desktop" <<EOL
[Desktop Entry]
Type=Application
Name=$APP_NAME
Exec=$APP_NAME
Icon=$APP_NAME
Comment=$APP_NAME Editor
Categories=Development;
Terminal=false
EOL

# İkonu kopyala
cp "$ICON_PATH" "$APPDIR/$APP_NAME.png"
cp "$ICON_PATH" "$APPDIR/usr/share/icons/hicolor/256x256/apps/$APP_NAME.png"

# ============================
# AppImage üret
# ============================
./linuxdeployqt-continuous-x86_64.AppImage "$APPDIR/usr/share/applications/$APP_NAME.desktop" \
    -appimage \
    -executable="$APPDIR/usr/bin/$APP_NAME" 

echo "✅ AppImage hazır!"

