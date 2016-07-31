FROM gcc:6.1.0

RUN apt-get update && \
    apt-get install -y man manpages-dev less netcat dnsutils
