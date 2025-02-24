#!/bin/bash

# Define the path to the miniRT executable
MINIRT="./miniRT"

# Directory containing scene files
SCENE_DIR="./scenes"

# Check if the scene directory exists
if [ ! -d "$SCENE_DIR" ]; then
  echo "Scene directory not found: $SCENE_DIR"
  exit 1
fi

# Iterate through the scene files and execute miniRT for each file
for scene_file in "$SCENE_DIR"/*; do
  if [ -f "$scene_file" ]; then
    echo "Running miniRT for file: $scene_file"
    $MINIRT "$scene_file"
  fi
done