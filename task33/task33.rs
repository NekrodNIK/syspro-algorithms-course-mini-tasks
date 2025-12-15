use std::mem;

#[derive(Debug, Clone)]
struct UnionFind {
    pub parent: Vec<usize>,
    pub rank: Vec<usize>,
    pub left: Vec<usize>,
}

#[derive(Debug, Clone, Copy, PartialEq)]
struct Task {
    pub deadline: usize,
    pub penalty: usize,
}

impl UnionFind {
    pub fn new(size: usize) -> Self {
        Self {
            parent: (0..size).collect(),
            rank: (0..size).map(|_| 0).collect(),
            left: (0..size).collect(),
        }
    }

    pub fn find(&mut self, x: usize) -> usize {
        if x != self.parent[x] {
            self.parent[x] = self.find(self.parent[x]);
        }

        self.parent[x]
    }

    pub fn leftmost(&mut self, mut x: usize) -> usize {
        x = self.find(x);
        self.left[x]
    }

    pub fn union(&mut self, mut x: usize, mut y: usize) {
        x = self.find(x);
        y = self.find(y);

        if x != y {
            if self.rank[x] < self.rank[y] {
                mem::swap(&mut x, &mut y);
            }

            self.left[x] = self.left[x].min(self.left[y]);
            self.parent[y] = x;

            if self.rank[x] == self.rank[y] {
                self.rank[x] += 1;
            }
        }
    }
}

impl Task {
    pub fn new(deadline: usize, penalty: usize) -> Self {
        Self { deadline, penalty }
    }
}

fn naive(tasks: &[Task], max_deadline: usize) -> (Vec<Option<Task>>, usize) {
    let mut schedule = vec![None; max_deadline];
    let mut total_penalty = 0;

    for task in tasks {
        match schedule[0..task.deadline].iter().position(|v| v.is_none()) {
            Some(ind) => schedule[ind] = Some(*task),
            None => total_penalty += task.penalty,
        }
        match schedule.iter().rev().position(|v| v.is_none()) {
            Some(ind) => schedule[ind] = Some(*task),
            None => total_penalty += task.penalty,
        }
    }

    (schedule, total_penalty)
}

fn solution(tasks: &[Task], max_deadline: usize) -> (Vec<Option<Task>>, usize) {
    let mut uf = UnionFind::new(max_deadline + 1);

    let mut schedule = vec![None; max_deadline];
    let mut total_penalty = 0;

    for task in tasks {
        let mut slot = uf.leftmost(task.deadline);

        if slot == 0 {
            total_penalty += task.penalty;
            slot = uf.leftmost(max_deadline);
            if slot == 0 {
                continue;
            }
        }

        schedule[slot - 1] = Some(task.clone());
        uf.union(slot, slot - 1);
    }

    (schedule, total_penalty)
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
        tasks.sort_by(|x, y| y.penalty.cmp(&x.penalty));

        let max_deadline = tasks.iter().map(|t| t.deadline).max().unwrap_or(0);
        let res = solution(&tasks, max_deadline);
        assert_eq!(res.1, 1);
        assert_eq!(
            res.0,
            [
                Some(Task::new(1, 100)),
                Some(Task::new(2, 1)),
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
        tasks.sort_by(|x, y| y.penalty.cmp(&x.penalty));

        let max_deadline = tasks.iter().map(|t| t.deadline).max().unwrap_or(0);
        let res = solution(&tasks, max_deadline);
        assert_eq!(res.1, 0);
        assert_eq!(
            res.0,
            [
                Some(Task::new(1, 3)),
                Some(Task::new(2, 2)),
                None,
                Some(Task::new(4, 1)),
                Some(Task::new(5, 1)),
            ]
        );

        let res = naive(&tasks, max_deadline);
        assert_eq!(res.1, 0);
        assert_ne!(
            res.0,
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
