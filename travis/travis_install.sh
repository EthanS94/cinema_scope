#!/usr/bin/bash
set -e

case $TRAVIS_OS_NAME in
    linux)
        # Download and run qt installer
        # (Thanks https://github.com/sgsaenger/vipster for example!)
        wget http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run -q -O qt_installer.run
        chmod +x qt_installer.run
        # Get the Qt Installer Framework Version
        QTIF_Version=`./qt_installer.run --version | grep "IFW Version" | perl -pe "s|IFW Version.*? (.*?\..*?)\..*?, .*|\1|g"`
        ./qt_installer.run -platform minimal --script $TRAVIS_BUILD_DIR/travis/navigate_qt_installer_linux.qs
        # Add installer framework to path
        export PATH="$HOME/Qt/Tools/QtInstallerFramework/${QTIF_Version}/bin:$PATH"
        ;;
    osx)
        sudo Xvfb :99 &
        brew update
        brew install qt5
        brew install doxygen
        wget http://download.qt.io/official_releases/online_installers/qt-unified-mac-x64-online.dmg -q -O qt_installer.dmg
        chmod +x qt_installer.dmg
        # Get the Qt Installer Framework Version
        QTIF_Version=`./qt_installer.run --version | grep "IFW Version" | perl -pe "s|IFW Version.*? (.*?\..*?)\..*?, .*|\1|g"`
        ./qt_installer.dmg -platform minimal --script $TRAVIS_BUILD_DIR/travis/navigate_qt_installer_mac.qs
        # Add installer framework to path
        export PATH="$HOME/Qt/Tools/QtInstallerFramework/${QTIF_Version}/bin:$PATH"
        ;;
    windows)
        # Download and run qt installer
        wget "http://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe" -q -O qt_installer.exe
        # Get the Qt Installer Framework Version
        QTIF_Version=`./qt_installer.exe --version | grep "IFW Version" | perl -pe "s|IFW Version.*? (.*?\..*?)\..*?, .*|\1|g"`
        ./qt_installer.exe --script $TRAVIS_BUILD_DIR/travis/navigate_qt_installer_windows.qs
        # Add Mingw and qt to path
        export MWDIR="/c/Users/travis/Qt/Tools/mingw730_64"
        export QTDIR="/c/Users/travis/Qt/5.12.2/mingw73_64"
        export QTIFW="/c/Users/travis/Qt/Tools/QtInstallerFramework/${QTIF_Version}"
        export PATH="$MWDIR/bin:$QTDIR/bin:$QTIFW/bin:$PATH"
        ;;
esac
