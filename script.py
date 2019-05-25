import sys
import subprocess
import os

prog_name = ["sequential", "parallel"]

for user, dir, files in os.walk('.'):
    if all(i in files for i in prog_name):
        for i in range(len(prog_name)):  # if run on Windows
            if os.name == "nt":
                prog_name[i] = prog_name[i] + ".exe."
                prog_name[i] = user + '\\' + prog_name[i]
            else:
                prog_name[i] = user + '/' + prog_name[i]
        break

def run(name, time_or_res):
    runs = subprocess.run([prog_name[name], sys.argv[2]], shell=False,
                                 stdout=subprocess.PIPE)
    return runs.stdout.decode().strip().split('\n')[time_or_res]

if __name__ == "__main__":
    time, times, result,  results = list(), list(), list(), list()
    print("The minimum result of each method in microseconds:")
    for amount in range(1, int(sys.argv[1]) + 1):
        times.append(run(0, 0))
        results.append(run(0, 1))
        time.append(run(1, 0))
        result.append(run(1, 1))
    print("Min time for sequential: {}".format(min(times)))
    print("Min time for parallel: {}".format(min(time)))
    print("Sequential program results are the same" if len(set(results))==1
          else "Sequential program results are different")
    print("Parallel program results are the same" if len(set(result))==1
          else "Parallel program results are different")
