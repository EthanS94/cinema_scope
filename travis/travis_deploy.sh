#!/usr/bin/bash
set -e

case $TRAVIS_OS_NAME in
    linux)
        ;;
    osx)
        if [[ "$osx_image" == "xcode10" ]]; then
          git clone "https://github.com/${TRAVIS_REPO_SLUG}"
          cd cinema_scope
          git checkout -b gh-pages origin/gh-pages
          git checkout master
          doxygen ./doxyfile.cfg
          git commit -am "Updating doxygen"
          git subtree split --prefix docs -b gh-pages-new
          git checkout gh-pages
          if git cherry-pick gh-pages-new; then
            git push "https://${GITHUB_TOKEN}@github.com/${TRAVIS_REPO_SLUG}" HEAD:gh-pages
          else
            echo "No changes to doxygen"
          fi
        fi
        ;;
    windows)
        ;;
esac
