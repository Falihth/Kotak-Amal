<?php
include 'koneksi.php'; // File koneksi ke database

if (isset($_GET['uang'])) {
    $uang = $_GET['uang'];

    // Simpan data ke database
    $sql = "UPDATE sensor SET nilai_sensor = '$uang' WHERE id = 1"; // Pastikan tabel dan kolom sesuai dengan database Anda
    if ($conn->query($sql) === TRUE) {
        echo "Data berhasil disimpan";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
    $conn->close();
} else {
    echo "Data tidak valid";
}
?>
