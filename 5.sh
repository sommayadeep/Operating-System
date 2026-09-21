#!/bin/bash

echo "Enter something:"
read n

if [[ $n =~ ^[0-9]+$ ]]
then
    echo "It is a number"
else
    echo "It is a string"
fi
