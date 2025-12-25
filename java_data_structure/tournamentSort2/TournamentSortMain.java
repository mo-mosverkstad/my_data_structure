package tournamentSort2;

import java.util.List;

public class TournamentSortMain {

    public static void main(String[] args) {
        List<Integer> list = List.of(35, 25, 50, 20, 15, 45, 10, 40, 1, 2);
        TournamentArray <Integer> array = new TournamentArray<>(list);

        System.out.println(array.sort());
    }
}
