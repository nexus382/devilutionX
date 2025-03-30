#!/bin/bash
# Converts Diablo audio files to ADPCM MS format for Dreamcast

# Check if ffmpeg is installed
if ! command -v ffmpeg &> /dev/null; then
    echo "Error: ffmpeg is not installed. Please install it first."
    exit 1
fi

# Ensure we have source and destination directories
if [ $# -lt 2 ]; then
    echo "Usage: $0 <source_dir> <destination_dir>"
    echo "Example: $0 ./diabdat/music ./build/data/diabdat/music"
    exit 1
fi

SOURCE_DIR=$1
DEST_DIR=$2

# Create destination directory if it doesn't exist
mkdir -p "$DEST_DIR"

# Process all WAV files in the source directory
find "$SOURCE_DIR" -name "*.wav" | while read -r file; do
    # Get relative path
    rel_path="${file#$SOURCE_DIR/}"
    # Create destination directory structure
    dest_file_dir="$DEST_DIR/$(dirname "$rel_path")"
    mkdir -p "$dest_file_dir"
    # Convert file
    dest_file="$DEST_DIR/$rel_path"
    echo "Converting $file to ADPCM MS format..."
    ffmpeg -y -i "$file" -acodec adpcm_ms "$dest_file" -loglevel error
done

# Process MP3 files (copy them as they are already compressed)
find "$SOURCE_DIR" -name "*.mp3" | while read -r file; do
    # Get relative path
    rel_path="${file#$SOURCE_DIR/}"
    # Create destination directory structure
    dest_file_dir="$DEST_DIR/$(dirname "$rel_path")"
    mkdir -p "$dest_file_dir"
    # Copy file
    dest_file="$DEST_DIR/$rel_path"
    echo "Copying compressed file $file..."
    cp "$file" "$dest_file"
done

echo "Conversion complete. Audio files are now optimized for Dreamcast."
echo "Place these files in your Dreamcast build directory." 