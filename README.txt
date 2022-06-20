## slscli

slscli <cnf_file_path>
slscli_static <cnf_file_path>
slscli_dynamic <cnf_file_path>

localsat solver.

Leider habe ich nicht mehr viel Zeit für die Doku, weil ich lange für die Änderungen gebraucht habe, die allocation dynamisch zu gestalten.
Die allokations Strategie kann in sls/sls/def.hpp geändert werden.

Außerdem werden von cmake die targets:
slscli, slscli_static und slscli_dynamic erstellt.

slscli - benutzt einen hybriden allocator, der bis zu einer obergrenze auf dem Stack allokiert und anschließend auf den heap zurück greift.
slscli_static - benutzt nut den stack.
slscli_dynamic - benutzt nut den heap.

## hidoku

hidoku_encoder <hidoku_string>
hidoku_solver <hidoku_string>

Das target hidoku_encoder erstellt für ein hidoku rätsel eine cnf.
Das target hidoku_solver lößt ein hidoku rätsel mit slscli.
