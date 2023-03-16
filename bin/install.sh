
DIR="$(cd "$(dirname "$0")" && pwd)"
echo 'Begin started'
echo '================================='
if sudo dpkg --get-selections | grep -q "^python3-pip[[:space:]]*install$" >/dev/null; then
if sudo apt-get -qq install python3-pip; then
    pip3 install pyelftools
else
    echo "Error installing"
fi
fi

echo '================= Running on Build ==========='

echo $0