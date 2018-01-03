#!/bin/bash

AWS_REGION="nyc3"
AWS_BUCKET="awooos"
#AWS_ACCESS_KEY="$1"
#AWS_SECRET_KEY="$2"

# Hard-code UID to 1000 so Jenkins is happy.
docker run -v "$(pwd):/tmp/work" -w /tmp/work \
  --env "AWS_REGION=${AWS_REGION}" \
  --env "AWS_BUCKET=${AWS_BUCKET}" \
  --env "AWS_ACCESS_KEY=${AWS_ACCESS_KEY}" \
  --env "AWS_SECRET_KEY=${AWS_SECRET_KEY}" \
  -u 1000 --rm -t whaledo/boto3 python3 ./bin/nightly/release.py
