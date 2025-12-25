use std::fmt::Debug;

fn merge_sorted_lists<T: Debug, F>(
    list1: &[T],
    list2: &[T],
    comparator: &F,
) -> Vec<T>
where
    T: Clone,
    F: Fn(&T, &T) -> isize,
{
    let mut result: Vec<T> = vec![];
    let mut index1: usize = 0;
    let mut index2: usize = 0;
    while index1 < list1.len() && index2 < list2.len() {
        let value1: &T = &list1[index1];
        let value2: &T = &list2[index2];
        if comparator(value1, value2) > 0 {
            result.push(value2.clone());
            index2 += 1;
        } else {
            result.push(value1.clone());
            index1 += 1;
        }
    }
    while index1 < list1.len() {
        result.push(list1[index1].clone());
        index1 += 1;
    }
    while index2 < list2.len() {
        result.push(list2[index2].clone());
        index2 += 1;
    }
    result
}

fn merge_sort<T: Debug + Clone, F>(list: &[T], comparator: &F) -> Vec<T>
where
    F: Fn(&T, &T) -> isize,
{
    let size: usize = list.len();
    if size == 0 {
        return vec![];
    }
    if size == 1 {
        return vec![list[0].clone()];
    }
    if size == 2 {
        let value0 = &list[0];
        let value1 = &list[1];
        if comparator(value0, value1) > 0 {
            return vec![value1.clone(), value0.clone()];
        }
        return vec![value0.clone(), value1.clone()];
    }

    let halfsize: usize = size / 2;
    let left: Vec<T> = merge_sort(&list[..halfsize], comparator);
    let right: Vec<T> = merge_sort(&list[halfsize..], comparator);

    merge_sorted_lists(&left[..], &right[..], comparator)
}

fn main() {
    let list1: Vec<u16> = vec![1, 2, 5, 7, 11];
    let list2: Vec<u16> = vec![3, 5, 6, 9, 10, 15];

    println!(
        "{:?}",
        merge_sorted_lists(
            &list1,
            &list2,
            &|x: &u16, y: &u16| -> isize { (*x as isize) - (*y as isize) }
        )
    );

    let list: Vec<u16> = vec![238, 283, 938, 198, 483, 737, 746, 828, 128];
    println!(
        "{:?}",
        merge_sort(&list, &|x: &u16, y: &u16| -> isize {
            (*x as isize) - (*y as isize)
        })
    );

    let slice: &[u16] = &list[1..4];
    println!("list length = {}, slice length = {}", list.len(), slice.len());
}
