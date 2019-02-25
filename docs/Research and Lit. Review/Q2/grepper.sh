#!/bin/bash 

for file in ./*; do
    if [[ "${file/.pdf}" == "$file" ]]; then
        echo "$file"
        pdftotext $file - | grep --with-filename --label=$file --color "There are five known load related problems"
    fi
done
