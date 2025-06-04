import importlib.util
import sys
import time

def run_day(day, is_test=False):
    day_str = str(day).zfill(2)  # Ensure two-digit format with leading zeros
    input_dir = "test_inputs" if is_test else "inputs"
    
    module_name = f"src.{day_str}"
    spec = importlib.util.spec_from_file_location(module_name, f"src/{day_str}.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    t1 = time.perf_counter()
    module.main(input_dir)
    t2 = time.perf_counter()
    print(f"Execution time: {t2-t1:0.4f} seconds")

if __name__ == "__main__":
    if len(sys.argv) > 3:
        print("Usage: python main.py <day>")
        sys.exit(1)

    day = sys.argv[1]
    
    # For testing, you can run with an additional argument like:
    # python main.py 01 test
    is_test = len(sys.argv) == 3 and sys.argv[2].lower() == "test"
    
    run_day(day, is_test)

