#!/bin/bash
cp ../42sh .
echo "test expansion simple"
echo "echo \$HOME"
echo "-----------------------------------------"
echo "echo \$HOME" | ./42sh
echo "echo \$HOME" | /bin/bash
echo "-----------------------------------------"
echo "test autre"
echo "-----------------------------------------"
echo "echo '$HOME'" | ./42sh
echo "echo '$HOME'" | /bin/bash
echo "-----------------------------------------"