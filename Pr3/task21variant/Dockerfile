FROM debian:latest

RUN apt-get update && apt-get install -y \
    bash \
    coreutils \
    procps \
    util-linux \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY test_limits.sh .

RUN chmod +x test_limits.sh

CMD ["/app/test_limits.sh"]
