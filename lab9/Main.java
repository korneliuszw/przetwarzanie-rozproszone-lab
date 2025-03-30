/**
 * Główna klasa programu implementującego model producent-konsument.
 * Program tworzy magazyn o ograniczonej pojemności oraz wątki producentów i konsumentów,
 * które współdzielą dostęp do magazynu.
 */
public class Main {
    public static void main(String[] args) {
        // Dostępne typy produktów
        String[] productTypes = {"Jabłko", "Banan", "Pomarańcza", "Gruszka", "Ananas"};
        
        // Tworzenie magazynu o pojemności 50
        Warehouse warehouse = new Warehouse(50);
        
        // Tworzenie producentów
        Thread[] producers = new Thread[3];
        for (int i = 0; i < producers.length; i++) {
            producers[i] = new Thread(new Producer("Producent-" + (i+1), warehouse, productTypes));
            producers[i].start();
        }
        
        // Tworzenie konsumentów
        Thread[] consumers = new Thread[5];
        for (int i = 0; i < consumers.length; i++) {
            consumers[i] = new Thread(new Consumer("Konsument-" + (i+1), warehouse, productTypes));
            consumers[i].start();
        }
        
        // Program będzie działał przez 30 sekund
        try {
            Thread.sleep(30000);
            
            // Zatrzymanie wątków
            for (Thread producer : producers) {
                producer.interrupt();
            }
            
            for (Thread consumer : consumers) {
                consumer.interrupt();
            }
            
            // Czekanie na zakończenie wątków
            for (Thread producer : producers) {
                producer.join();
            }
            
            for (Thread consumer : consumers) {
                consumer.join();
            }
            
            System.out.println("Program zakończony.");
            
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
} 