import timeit
import functools

def fibonacci_unoptimized(n):
    if n <= 1:
        return max(n, 0)

    return fibonacci_unoptimized(n-1) + fibonacci_unoptimized(n-2)


@functools.cache
def fibonacci_optimized(n):
    if n <= 1:
        return max(n, 0)

    return fibonacci_optimized(n-1) + fibonacci_optimized(n-2)

stmt_code_unoptimized = "fibonacci_unoptimized(40)"
stmt_code_optimized = "fibonacci_optimized(40)"

dictio = {
    "fibonacci_optimized": fibonacci_optimized,
    "fibonacci_unoptimized": fibonacci_unoptimized
}

t_u = timeit.Timer(stmt=stmt_code_unoptimized, globals=dictio)
t_o = timeit.Timer(stmt=stmt_code_optimized, globals=dictio)

total_time_unoptimized = t_u.timeit(number=5)
total_time_optimized = t_o.timeit(number=5)



print(f"Tempo total (não otimizado) = {total_time_unoptimized}")
print(f"Tempo total (otimizado) = {total_time_optimized}\n")

print(f"Tempo médio (não otimizado) = {total_time_unoptimized/5}")
print(f"Tempo médio (otimizado) = {total_time_optimized/5}")
