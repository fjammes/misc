#!/bin/bash

set -euxo pipefail

KUBEDB_VERSION="0.13.0-rc.0"

# See https://kubedb.com/docs/0.12.0/setup/install/
curl -fsSL "https://raw.githubusercontent.com/kubedb/cli/$KUBEDB_VERSION/hack/deploy/kubedb.sh" | bash
kubectl get pods -n kube-system | grep kubedb-operator

kubectl wait pods --all-namespaces -l app=kubedb
kubectl get crd -l app=kubedb

wget -O kubedb "https://github.com/kubedb/cli/releases/download/$KUBEDB_VERSION/kubedb-linux-amd64" \
  && chmod +x kubedb \
  && sudo mv kubedb /usr/local/bin/

# See https://kubedb.com/docs/v0.13.0-rc.0/guides/redis/quickstart/quickstart/
kubectl create ns demo
kubectl get redisversions
kubedb create -f https://github.com/kubedb/docs/raw/v0.13.0-rc.0/docs/examples/redis/quickstart/demo-1.yaml
kubedb get rd -n demo

kubectl exec -it redis-quickstart-0 -n demo sh