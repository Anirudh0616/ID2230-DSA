struct Heap {
    arr: Vec<i32>,
}

impl Heap {
    fn new(nums: Vec<i32>) -> Self {
        let mut heap = Heap { arr: nums };
        let size = heap.arr.len();
        if size > 1 {
            let mut i = (size - 2)/ 2;
            loop {
                heap.max_heapify(i);
                if i == 0 {
                    break;
                }
                i -= 1;
            }
        }
        heap
    }

    fn max_heapify(&mut self, index: usize) {
        let size = self.arr.len();

        let left = index * 2 + 1;
        let right = index * 2 + 2;
        let mut max = index;

        if left < size && self.arr[left] > self.arr[max]{
            max = left;
        }
        if right < size && self.arr[right] > self.arr[max]{
            max = right;
        }

        if max != index {
            self.arr.swap(max, index);
            self.max_heapify(max);
        }
    }

    fn sift_up(arr: &mut Vec<i32>, index: usize) {
        if index == 0 {
            return;
        }
        let parent = (index - 1) / 2;
        if arr[index] > arr[parent] {
            arr.swap(index, parent);
            Self::sift_up(arr, parent);
        }
    }

    fn insert(&mut self, data: i32) {
        self.arr.push(data);
        let idx = self.arr.len() - 1;
        Self::sift_up(&mut self.arr, idx)
    }

    fn pop_max(&mut self) -> Option<i32> {
        if self.arr.is_empty() {
            return None;
        }
        let size = self.arr.len();
        self.arr.swap(0, size - 1);
        let max = self.arr.pop();

        if !self.arr.is_empty() {
            self.max_heapify(0);
        }
        max
    }
    fn print_heap(&self) {
        let size = self.arr.len();
        if size == 0 {
            println!("Heap Empty");
            return;
        }

        println!("Printing Heap:");

        let mut level = 0;
        let mut next_break = 1; // same as your C code

        for (i, val) in self.arr.iter().enumerate() {
            print!("{} ", val);

            if i + 1 == next_break {
                println!();
                level += 1;
                next_break += 1 << level; // 2^level
            }
        }

        println!();
    }
}

fn main() {
    let nums = vec![1,2,3,4,5,6,7,8,9];
    let mut heap = Heap::new(nums);

    for i in 0..=9 {
        if i % 3 == 0 {
            heap.insert(i * 10);
        }
        heap.print_heap();
        let popped = heap.pop_max();
        println!("Popped: {:?}", popped);
    }
}
