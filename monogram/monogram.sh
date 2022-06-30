#!/bin/bash

monogram_encoder=~/sat/localsat/cmake-build-release/bin/monogram_encoder
monogram_decoder=~/sat/localsat/cmake-build-release/bin/monogram_decoder
solver=~/cadical/build/cadical

${monogram_encoder} $1 | \
${solver}              | \
grep ^[sv]             | \
xargs ${monogram_decoder} $1
