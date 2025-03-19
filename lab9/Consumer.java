import java.util.Random;

/**
 * Klasa reprezentująca konsumenta, który pobiera towary z magazynu.
 */
public class Consumer implements Runnable {
    private final Warehouse warehouse;
    private final String[] productTypes;
    private final String name;
    private final Random random;

    /**
     * Tworzy nowego konsumenta.
     * 
     * @param name nazwa konsumenta
     * @param warehouse magazyn, z którego konsument pobiera towary
     * @param productTypes typy produktów, które konsument może pobierać
     */
    public Consumer(String name, Warehouse warehouse, String[] productTypes) {
        this.name = name;
        this.warehouse = warehouse;
        this.productTypes = productTypes;
        this.random = new Random();
    }

    @Override
    public void run() {
        while (!Thread.currentThread().isInterrupted()) {
            try {
                // Losowy czas między zakupami
                Thread.sleep(random.nextInt(2000) + 1000);
                
                // Losowy typ produktu
                String productType = productTypes[random.nextInt(productTypes.length)];
                
                // Losowa ilość produktu (1-5)
                int requestedQuantity = random.nextInt(5) + 1;
                
                int actualQuantity = warehouse.getProduct(productType, requestedQuantity);
                
                if (actualQuantity > 0) {
                    if (actualQuantity == requestedQuantity) {
                        System.out.println(name + " zakupił " + actualQuantity + " sztuk produktu " + productType);
                    } else {
                        System.out.println(name + " zakupił częściowo " + actualQuantity + "/" + requestedQuantity + 
                                           " sztuk produktu " + productType);
                    }
                } else {
                    System.out.println(name + " nie mógł zakupić produktu " + productType + " - brak w magazynie");
                }
                
                // Wyświetl stan magazynu
                System.out.println("Stan magazynu: " + warehouse.getCurrentOccupancy() + "/" + warehouse.getCapacity());
                
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
} 