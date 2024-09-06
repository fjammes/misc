#!/bin/bash

set -euxo pipefail

curl -L \
  -X POST \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer $TOKEN" \
  -H "X-GitHub-Api-Version: 2022-11-28" \
  https://api.github.com/repos/fjammes/misc/dispatches \
  -d '{"event_type":"e2e-science","client_payload":{"build":true,"e2e":true}}'
