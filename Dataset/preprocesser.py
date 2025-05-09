import csv

with open("soc-sign-bitcoinotc.csv", "r") as infile, open("../Dataset/bitcoin_weighted_edges.txt", "w") as outfile:
    reader = csv.reader(infile)
    for row in reader:
        source, target, weight = row[0], row[1], row[2]
        outfile.write(f"{source} {target} {weight}\n")
