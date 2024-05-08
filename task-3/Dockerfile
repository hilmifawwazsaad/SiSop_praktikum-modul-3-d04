# Base Image
FROM gcc:latest

# Set working directory
WORKDIR /APP

# Copy chat.c to working directory
COPY chat.c .

# Set execute permission
RUN chmod +x chat.c

# Compile chat.c
RUN gcc -o chat chat.c -pthread

# Run the application
CMD ["./chat"]

# # Create a Volume shared
# VOLUME /shared

# # Set entrypoint to run an interactive shell
# ENTRYPOINT ["/bin/sh"]