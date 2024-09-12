#!/bin/bash

set -euxo pipefail

url="https://api.github.com/repos/fjammes/misc/dispatches"

token=$1

build=true
e2e=true
push=true
cluster_name="kind"
image="fjammes/science:latest"

payload="{\"build\": $build,\"e2e\": $e2e,\"push\": $push, \"cluster_name\": \"$cluster_name\", \"image\": \"$image\"}"
echo "Payload: $payload"

if [ -z "$token" ]; then
  echo "No token provided, skipping GitHub dispatch"
else
  echo "Dispatching event to GitHub"
  curl -L \
  -X POST \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer $token" \
  -H "X-GitHub-Api-Version: 2022-11-28" \
  $url \
  -d "{\"event_type\":\"e2e-science\",\"client_payload\":$payload}" || echo "ERROR Failed to dispatch event" >&2
fi

