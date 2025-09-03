/* Dosya temelli bankacılık sistemi
Bu program hesap oluşturma, para yatırma, para çekme, para transferi, bakiye öğrenme ve çıkış işlemlerini içeren bir menü tabanlı sistemdir.

Öncelikle kullanıcının hesap numarası, adı, soyadı, şifresi ve bakiye bilgilerini tutan bir struct tanımlanmıştır.

** Menüdeki işlemler için aşağıdaki fonksiyonlar yazılmıştır:
- Hesap oluşturma -> createacc
- Para yatırma -> deposit
- Para çekme -> withdraw
- Para transferi -> transfer
- Bakiye öğrenme -> showbalance

** Ayrıca her kullanıcıya 0'dan 1000'e kadar rastgele bir hesap numarası atanmasını sağlayan generateaccountno fonksiyonu yazılmıştır. 
Bu fonksiyon, oluşturulan numaranın daha önce başka bir kullanıcıya verilmemiş olmasını kontrol eder.

main() içinde kullanıcıya menü işlemleri sunulur ve çıkış seçeneği seçilmediği sürece, döngü kullanılarak kullanıcıya tekrar tekrar işlem yapma imkanı tanınır. 
Her kullanıcıya sadece bir kez srand() ile rastgele sayı üretimi için tohum değeri atanır.

createacc() fonksiyonunda kullanıcıdan ad, soyad, şifre ve başlangıç bakiyesi bilgileri alınır. Hesap başarıyla oluşturulursa kullanıcıya hesap numarası verilir.

deposit() fonksiyonunda kullanıcıdan hesap numarası ve şifre istenir. Doğru bilgi girildikten sonra yatırılmak istenen miktar alınır. 
Miktar 0’dan büyükse para hesaba yatırılır, aksi halde hata mesajı gösterilir. İşlem sonunda güncel bakiye kullanıcıya bildirilir.

withdraw() fonksiyonunda kullanıcıdan hesap numarası ve şifre istenir. Çekilmek istenen miktar 0’dan büyük ve bakiyeden küçük/eşit olduğu durumda işlem yapılır, 
aksi halde hata mesajı gösterilir. İşlem sonunda güncel bakiye kullanıcıya bildirilir.

transfer() fonksiyonunda gönderenin hesap numarası ve şifresi doğrulanır. Yeterli bakiye varsa kullanıcıdan alıcının hesap numarası alınır. 
Alıcının hesabı bulunursa miktar transfer edilir, aksi halde işlem iptal edilerek para gönderenin hesabına iade edilir.

showbalance() fonksiyonunda kullanıcıdan hesap numarası ve şifre istenir. Doğru bilgi girildiyse bakiyesi gösterilir.

Dosya işlemleri için "accounts.dat" isimli bir dosya kullanılmaktadır.
- "ab" modu: Dosyaya yeni kayıt eklemek için (binary modunda).
- "rb" veya "rb+" modları: Dosyayı okumak veya hem okuma/hem yazma yapmak için.
*/
