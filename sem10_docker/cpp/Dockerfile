# Command to build image:
# docker build -t tp_cpp .
# Command to run container:
# docker run -it --rm --name tp_cpp --entrypoint ./main tp_cpp
# (output must be "Hello from docker")

FROM alpine:latest AS build

COPY ./ /

RUN apk add --no-cache g++ && \
  mkdir app && \
  g++ src/main.cpp -o /app/main && \
  apk del g++

FROM alpine:latest

COPY --from=build /app/main /app/main
# Shared libraries for running main
RUN apk add --no-cache libstdc++

# Add user
RUN addgroup -g 1000 -S devops2024user && \
adduser -u 1000 -S devops2024user -G devops2024user && \
chown -R devops2024user:devops2024user \
    /app

WORKDIR /app

USER devops2024user

# RUN g++ src/main.cpp -o main
# RUN apk del g++

# ENTRYPOINT ["./main"]
# ENTRYPOINT ["/bin/bash"]
