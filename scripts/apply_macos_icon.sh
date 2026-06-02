#!/bin/bash
set -u

TARGET_PATH="${1:-}"
SOURCE_IMAGE="${2:-}"

if [[ -z "$TARGET_PATH" || -z "$SOURCE_IMAGE" ]]; then
  echo "[Reaction Lab] Icon script skipped: missing target path or source image."
  exit 0
fi

if [[ ! -f "$TARGET_PATH" ]]; then
  echo "[Reaction Lab] Icon script skipped: target executable not found at '$TARGET_PATH'."
  exit 0
fi

if [[ ! -f "$SOURCE_IMAGE" ]]; then
  echo "[Reaction Lab] Icon script skipped: source image not found at '$SOURCE_IMAGE'."
  exit 0
fi

if [[ "$(uname)" != "Darwin" ]]; then
  echo "[Reaction Lab] Icon script skipped: macOS only."
  exit 0
fi

for cmd in sips iconutil xcrun; do
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "[Reaction Lab] Icon script skipped: '$cmd' ontbreekt."
    echo "Installeer Xcode Command Line Tools met: xcode-select --install"
    exit 0
  fi
done

TMP_DIR="$(mktemp -d /tmp/reactionlab_icon.XXXXXX)"
ICONSET_DIR="$TMP_DIR/ReactionLab.iconset"
ICNS_PATH="$TMP_DIR/ReactionLab.icns"
mkdir -p "$ICONSET_DIR"

cleanup() {
  rm -rf "$TMP_DIR"
}
trap cleanup EXIT

make_icon_pair() {
  local base_size="$1"
  local double_size=$((base_size * 2))
  sips -z "$base_size" "$base_size" "$SOURCE_IMAGE" --out "$ICONSET_DIR/icon_${base_size}x${base_size}.png" >/dev/null
  sips -z "$double_size" "$double_size" "$SOURCE_IMAGE" --out "$ICONSET_DIR/icon_${base_size}x${base_size}@2x.png" >/dev/null
}

make_icon_pair 16
make_icon_pair 32
make_icon_pair 128
make_icon_pair 256
make_icon_pair 512

if ! iconutil -c icns "$ICONSET_DIR" -o "$ICNS_PATH"; then
  echo "[Reaction Lab] Icon script skipped: kon .icns niet maken."
  exit 0
fi

if ! sips -i "$ICNS_PATH" >/dev/null; then
  echo "[Reaction Lab] Waarschuwing: sips kon icon metadata niet zetten."
fi

RSRC_FILE="$TMP_DIR/ReactionLabIcon.rsrc"

if ! xcrun DeRez -only icns "$ICNS_PATH" > "$RSRC_FILE" 2>/dev/null; then
  echo "[Reaction Lab] Icon script skipped: DeRez mislukt."
  exit 0
fi

if ! xcrun Rez -append "$RSRC_FILE" -o "$TARGET_PATH" 2>/dev/null; then
  echo "[Reaction Lab] Icon script skipped: Rez mislukt."
  exit 0
fi

if ! xcrun SetFile -a C "$TARGET_PATH" 2>/dev/null; then
  echo "[Reaction Lab] Icon toegevoegd, maar SetFile mislukte."
  exit 0
fi

echo "[Reaction Lab] Custom macOS icon succesvol toegepast op: $TARGET_PATH"
