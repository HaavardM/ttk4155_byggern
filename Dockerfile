FROM haavardm/ttk4115_byggern:0.1

COPY ./ ./
RUN make
