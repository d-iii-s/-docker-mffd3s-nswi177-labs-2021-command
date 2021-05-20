FROM alpine:3.13 AS build
COPY checksum.c /root/
RUN cd /root/ \
    && apk add musl-dev gcc openssl-dev libcrypto1.1 \
    && gcc checksum.c -lcrypto

FROM alpine:3.13
MAINTAINER horky@d3s.mff.cuni.cz
LABEL maintainer="horky@d3s.mff.cuni.cz"

COPY --from=build /root/a.out /usr/local/bin/nswi177-task-command

RUN apk add libcrypto1.1
CMD echo "Run with -it /bin/sh"
