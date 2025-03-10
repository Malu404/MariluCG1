import re

def rotate_vertex(x, y, z):
    # Aplica a rotação de 90 graus em torno do eixo Y
    x_new = z
    y_new = y
    z_new = -x
    return x_new, y_new, z_new

def process_obj_file(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            if line.startswith('v '):  # Verifica se a linha é um vértice
                parts = line.split()
                x = float(parts[1])
                y = float(parts[2])
                z = float(parts[3])
                x_new, y_new, z_new = rotate_vertex(x, y, z)
                outfile.write(f"v {x_new} {y_new} {z_new}\n")
            else:
                outfile.write(line)

# Substitua 'teapot.obj' pelo nome do seu arquivo de entrada
input_file = 'teapot400.obj'
output_file = 'teapot_rotated.obj'

process_obj_file(input_file, output_file)