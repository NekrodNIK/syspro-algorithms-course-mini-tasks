use std::mem;
use std::ops::ControlFlow;

#[derive(Debug, Clone, Default)]
struct Unit {
    parent: usize,
    rank: usize,
}

#[derive(Debug, Clone, Default)]
struct UnionFind {
    vec: Vec<Unit>,
}

impl UnionFind {
    pub fn new(size: usize) -> Self {
        let mut vec = vec![Unit::default(); size];

        for i in 0..size {
            vec[i].parent = i;
        }

        return Self { vec };
    }

    pub fn find(&mut self, x: usize) -> usize {
        if x >= self.vec.len() {
            return 0;
        }

        let mut root = self.vec[x].parent;
        while self.vec[root].parent != root {
            root = self.vec[root].parent;
        }

        let mut node = x;
        while self.vec[node].parent != root {
            let p = self.vec[node].parent;
            self.vec[node].parent = root;
            node = p;
        }

        root
    }

    pub fn union(&mut self, mut x: usize, mut y: usize) -> bool {
        x = self.find(x);
        y = self.find(y);

        if x == y {
            return false;
        }

        if self.vec[x].rank > self.vec[y].rank {
            mem::swap(&mut x, &mut y);
        }

        if self.vec[x].rank == self.vec[y].rank {
            self.vec[x].rank += 1;
        }

        self.vec[x].parent = y;
        true
    }
}

#[derive(Debug, Clone, Default, PartialEq)]
struct Task {
    pub deadline: usize,
    pub penalty: usize,
}

impl Task {
    pub fn new(deadline: usize, penalty: usize) -> Self {
        Self { deadline, penalty }
    }
}

#[derive(Debug, Clone)]
struct Res {
    pub schedule: Vec<Option<Task>>,
    pub total_penalty: usize,
}

fn naive(tasks: &[Task]) -> Res {
    let max = tasks[0].deadline;

    let mut schedule = vec![None; max];
    let mut total_penalty = 0;

    for task in tasks {
        let status = (1..task.deadline).try_for_each(|i| {
            if schedule[i].is_none() {
                schedule[i] = Some(task.clone());
                return ControlFlow::Break(());
            }
            ControlFlow::Continue(())
        });

        if status.is_continue() {
            total_penalty += task.penalty;
        }
    }

    Res {
        schedule,
        total_penalty,
    }
}

fn solution(tasks: &[Task]) -> Res {
    let max = tasks[0].deadline;
    let mut uf = UnionFind::new(max + 1);

    let mut schedule = vec![None; max];
    let mut total_penalty = 0;

    for task in tasks {
        let mut slot = uf.find(task.deadline);

        if slot == 0 {
            total_penalty += task.penalty;
            slot = uf.find(max);
            if slot == 0 {
                continue;
            }
        }

        schedule[slot - 1] = Some(task.clone());
        uf.union(slot, slot - 1);
    }

    Res {
        schedule,
        total_penalty,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_base() {
        let mut tasks = [
            Task::new(1, 100),
            Task::new(2, 1),
            Task::new(3, 1),
            Task::new(3, 1),
        ];
        tasks.sort_by(|x, y| y.deadline.cmp(&x.deadline));

        let res = solution(&tasks);
        assert_eq!(res.total_penalty, 100);
        assert_eq!(
            res.schedule,
            [
                Some(Task::new(2, 1)),
                Some(Task::new(3, 1)),
                Some(Task::new(3, 1)),
            ]
        );
    }

    #[test]
    fn test_compare() {
        let mut tasks = [
            Task::new(1, 3),
            Task::new(2, 2),
            Task::new(5, 1),
            Task::new(4, 1),
        ];
        tasks.sort_by(|x, y| y.deadline.cmp(&x.deadline));

        let res = solution(&tasks);
        assert_eq!(res.total_penalty, 0);
        assert_eq!(
            res.schedule,
            [
                Some(Task::new(1, 3)),
                Some(Task::new(2, 2)),
                None,
                Some(Task::new(4, 1)),
                Some(Task::new(5, 1)),
            ]
        );

        let res = naive(&tasks);
        assert_eq!(res.total_penalty, 5);
        assert_ne!(
            res.schedule,
            [
                Some(Task::new(1, 3)),
                Some(Task::new(2, 2)),
                None,
                Some(Task::new(4, 1)),
                Some(Task::new(5, 1)),
            ]
        )
    }
}
