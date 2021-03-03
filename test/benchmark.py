import subprocess


def gettime(bin, file):
    return float(subprocess.run("./{} {} | tail -n 1".format(bin, file),
                                capture_output=True,
                                shell=True,
                                text=True).stdout)


def gettime_avg(bin, file):
    # set loop count
    cnt = 5
    
    # loop and accumulate time
    sum = 0
    for i in range(cnt):
        sum = sum + gettime(bin, file)        
        
    # divide to get avg
    return sum / cnt


def main():
    # put user at ease
    print("benchmarking...")

    # define variables
    h = "h"
    hf = "hf"

    fsmall = "cpu.c"
    flarge = "nbio_7_2_0_sh_mask.h"

    unit = "milliseconds"

    # compile
    subprocess.run("gcc ../hexembed.c -o {}".format(h), shell=True)
    subprocess.run("gcc ../hexembed_fast.c -o {}".format(hf), shell=True)

    # test one off (small)
    h_time_small = gettime(h, fsmall)
    hf_time_small = gettime(hf, fsmall)

    # test one off (large)
    h_time_large = gettime(h, flarge)
    hf_time_large = gettime(hf, flarge)

    # test average (small file)
    h_time_small_avg = gettime_avg(h, fsmall)
    hf_time_small_avg = gettime_avg(hf, fsmall)

    # test average (large file)
    h_time_large_avg = gettime_avg(h, flarge)
    hf_time_large_avg = gettime_avg(hf, flarge)

    # report findings
    print()
    print("Time for one file (small):")
    print("hexembed     : {:.3f} {}".format(h_time_small, unit))
    print("hexembed_fast: {:.3f} {}".format(hf_time_small, unit))
    print()
    print("Time for one file (large):")
    print("hexembed     : {:.3f} {}".format(h_time_large, unit))
    print("hexembed_fast: {:.3f} {}".format(hf_time_large, unit))
    print()
    print("Average time per file (small):")
    print("hexembed     : {:.3f} {}".format(h_time_small_avg, unit))
    print("hexembed_fast: {:.3f} {}".format(hf_time_small_avg, unit))
    print()
    print("Average time per file (large):")
    print("hexembed     : {:.3f} {}".format(h_time_large_avg, unit))
    print("hexembed_fast: {:.3f} {}".format(hf_time_large_avg, unit))
    print()

if __name__ == "__main__":
    # execute only if run as a script
    main()

    
