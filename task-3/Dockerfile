# Base Image
FROM alpine:latest

# Install Dependencies
RUN apk update && \
    apk add --no-cache gcc libc-dev

# Set working directory
WORKDIR /dockermessage

# Copy chat.c to working directory
COPY chat.c .

# Set execute permission
RUN chmod +x chat.c

# Compile chat.c
RUN gcc -o chat chat.c

# Run the application
CMD ["./chat"]