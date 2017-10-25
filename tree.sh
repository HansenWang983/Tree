#!/bin/bash
dot ./code/before.dot -Tpng -o ./graph/before.png
dot ./code/after.dot -Tpng -o ./graph/after.png
open ./graph/before.png
open ./graph/after.png


