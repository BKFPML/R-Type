#!/bin/bash

doxygen Doxyfile

mv docs/html/index.html ./technical_documentation.html
