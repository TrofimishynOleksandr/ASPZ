FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN gcc lottery.c -o lottery

CMD ["/bin/bash", "-c", "\
    echo '$ prlimit ./lottery'; prlimit ./lottery"]