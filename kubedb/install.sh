#!/bin/bash

set -euxo pipefail

KUBEDB_VERSION="v0.13.0-rc.0"

# See https://kubedb.com/docs/0.12.0/setup/install/
curl -fsSL https://raw.githubusercontent.com/kubedb/installer/89fab34cf2f5d9e0bcc3c2d5b0f0599f94ff0dca/deploy/kubedb.sh | bash
kubectl get pods -n kube-system | grep kubedb-operator

kubectl  wait --for=condition=Ready pods -l app=kubedb --all-namespaces
kubectl get crd -l app=kubedb

wget -O kubedb https://github.com/kubedb/cli/releases/download/$KUBEDB_VERSION/kubedb-linux-amd64 \
  && chmod +x kubedb \
  && sudo mv kubedb /usr/local/bin/

# See https://kubedb.com/docs/v0.13.0-rc.0/guides/redis/quickstart/quickstart/
kubectl create ns demo
kubectl get redisversions
# Example provided in documentation is broken;
# https://github.com/kubedb/docs/raw/v0.13.0-rc.0/docs/examples/redis/quickstart/demo-1.yaml
kubectl apply -f demo.yaml
kubedb get rd -n demo

kubectl exec -it redis-quickstart-0 -n demo sh
