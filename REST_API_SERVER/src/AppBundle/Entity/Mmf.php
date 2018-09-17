<?php

namespace AppBundle\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Mmf
 *
 * @ORM\Table(name="mmf")
 * @ORM\HasLifecycleCallbacks
 * @ORM\Entity(repositoryClass="AppBundle\Repository\MmfRepository")
 */
class Mmf
{
    /**
     * @var int
     *
     * @ORM\Column(name="id", type="integer")
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="AUTO")
     */
    private $id;

    /**
     * @var int
     *
     * @ORM\Column(name="timestamp", type="bigint")
     */
    private $timestamp;

    /**
     * @var string
     *
     * @ORM\Column(name="mac", type="string", length=18, nullable=true)
     */
    private $mac;

    /**
     * @var int
     *
     * @ORM\Column(name="rssi", type="smallint", nullable=true)
     */
    private $rssi;

    /**
     * @var string
     *
     * @ORM\Column(name="bssid", type="string", length=18, nullable=true)
     */
    private $bssid;

    /**
     * @var string
     *
     * @ORM\Column(name="ssid", type="string", length=32, nullable=true)
     */
    private $ssid;

    /**
     * @var int
     *
     * @ORM\Column(name="rssi_min", type="smallint", nullable=true)
     */
    private $rssiMin;

    /**
     * @var int
     *
     * @ORM\Column(name="rssi_max", type="smallint", nullable=true)
     */
    private $rssiMax;

    /**
     * @var int
     *
     * @ORM\Column(name="sensor_id", type="smallint")
     */
    private $sensorId;

    /**
     * @var \DateTime
     *
     * @ORM\Column(name="timestamp_received", type="datetime")
     */
    private $timestampReceived;


    /**
     * Get id
     *
     * @return int
     */
    public function getId()
    {
        return $this->id;
    }

    /**
     * Set timestamp
     *
     * @param integer $timestamp
     *
     * @return Mmf
     */
    public function setTimestamp($timestamp)
    {
        $this->timestamp = $timestamp;

        return $this;
    }

    /**
     * Get timestamp
     *
     * @return int
     */
    public function getTimestamp()
    {
        return $this->timestamp;
    }

    /**
     * Set mac
     *
     * @param string $mac
     *
     * @return Mmf
     */
    public function setMac($mac)
    {
        $this->mac = $mac;

        return $this;
    }

    /**
     * Get mac
     *
     * @return string
     */
    public function getMac()
    {
        return $this->mac;
    }

    /**
     * Set rssi
     *
     * @param integer $rssi
     *
     * @return Mmf
     */
    public function setRssi($rssi)
    {
        $this->rssi = $rssi;

        return $this;
    }

    /**
     * Get rssi
     *
     * @return int
     */
    public function getRssi()
    {
        return $this->rssi;
    }

    /**
     * Set bssid
     *
     * @param string $bssid
     *
     * @return Mmf
     */
    public function setBssid($bssid)
    {
        $this->bssid = $bssid;

        return $this;
    }

    /**
     * Get bssid
     *
     * @return string
     */
    public function getBssid()
    {
        return $this->bssid;
    }

    /**
     * Set ssid
     *
     * @param string $ssid
     *
     * @return Mmf
     */
    public function setSsid($ssid)
    {
        $this->ssid = $ssid;

        return $this;
    }

    /**
     * Get ssid
     *
     * @return string
     */
    public function getSsid()
    {
        return $this->ssid;
    }

    /**
     * Set rssiMin
     *
     * @param integer $rssiMin
     *
     * @return Mmf
     */
    public function setRssiMin($rssiMin)
    {
        $this->rssiMin = $rssiMin;

        return $this;
    }

    /**
     * Get rssiMin
     *
     * @return int
     */
    public function getRssiMin()
    {
        return $this->rssiMin;
    }

    /**
     * Set rssiMax
     *
     * @param integer $rssiMax
     *
     * @return Mmf
     */
    public function setRssiMax($rssiMax)
    {
        $this->rssiMax = $rssiMax;

        return $this;
    }

    /**
     * Get rssiMax
     *
     * @return int
     */
    public function getRssiMax()
    {
        return $this->rssiMax;
    }

    /**
     * Set sensorId
     *
     * @param integer $sensorId
     *
     * @return Mmf
     */
    public function setSensorId($sensorId)
    {
        $this->sensorId = $sensorId;

        return $this;
    }

    /**
     * Get sensorId
     *
     * @return int
     */
    public function getSensorId()
    {
        return $this->sensorId;
    }

    /**
     * Set timestampReceived
     *
     * @param \DateTime $timestampReceived
     *
     * @return Mmf
     */
    public function setTimestampReceived($timestampReceived)
    {
        $this->timestampReceived = $timestampReceived;

        return $this;
    }

    /**
     * Get timestampReceived
     *
     * @return \DateTime
     */
    public function getTimestampReceived()
    {
        return $this->timestampReceived;
    }
    /**
    *
    * @ORM\PrePersist
    */
    public function updatedTimestamps()
    {

        if ($this->getTimestampReceived() == null) {
            $this->setTimestampReceived(new \DateTime('now'));
        }
    }
}

