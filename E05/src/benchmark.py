import random
import time
import timeit


ARRAY_SIZE = 10000  # era 100000 mas python é paia e demorou demais

NUMBER_OF_RUNS = 5


def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def selection_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[min_idx], arr[i] = arr[i], arr[min_idx]

def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j = j - 1
        arr[j + 1] = key


def generate_random_array(n):
    return [random.randint(0, 9999) for _ in range(n)]

def print_array(arr):
    n = len(arr)
    print("Elementos do array: ", end="")
    
    for i in range(n):
        print(f"{arr[i]} ", end="")
    print()

def benchmark_sort(sort_function, original_array, number_of_runs):
    sort_name = sort_function.__name__

    setup_code = "arr_to_sort = original_array.copy()"

    stmt_code = "sort_function(arr_to_sort)"

    globals_dict = {
        "original_array": original_array,
        "sort_function": sort_function
    }

    t = timeit.Timer(stmt=stmt_code, setup=setup_code, globals=globals_dict) # não da para printar aqui dentro

    try:
        total_time = t.timeit(number=number_of_runs)
        
        avg_time = total_time / number_of_runs
        print(f"# Runs: {number_of_runs}\nTempo: {total_time:.4f} segundos")
        print(f"Média tempo/run: {avg_time:.4f} segundos\n")
        return avg_time
    except Exception:
        return None


def main():
    random.seed(time.time())
    
    original_array = generate_random_array(ARRAY_SIZE)

    results = {}
    results["bubble_sort"] = benchmark_sort(bubble_sort, original_array, NUMBER_OF_RUNS)
    results["selection_sort"] = benchmark_sort(selection_sort, original_array, NUMBER_OF_RUNS)
    results["insertion_sort"] = benchmark_sort(insertion_sort, original_array, NUMBER_OF_RUNS)

    for name, avg_time in results.items():
        if avg_time is not None:
            print(f"{name}: {avg_time:.4f} segundos (média)")

if __name__ == "__main__":
    main()
